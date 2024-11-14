#include "gs.h"  ///< 假设 gs.h 是声明变量和函数的头文件

#include <typeinfo>


TEST(Initialization, DefaultValues) {
    init();

//test initial u
    for (const auto& row : u) {
        for (double val : row) {
            EXPECT_EQ(val, 1.0);
        }
    }
//test v whether in the (0,1) range in the code area
    for (int i = 100; i <= 200; i++)
    {
        for (int j = 100; j <= 150; j++) {
            EXPECT_GE(v[i][j], 0);
            EXPECT_LT(v[i][j], 1);

    }

    }
//test v in other area
    for (int i = 0; i < 100 && i>200 &&  i<width; i++)
    {
        for (int j = 0; j<100 && j>150 && j <height; j++) {
            EXPECT_EQ(v[i][j], 0);
            

        }

    }
    EXPECT_EQ(u.size(), v.size());
    EXPECT_EQ(u[0].size(), v[0].size());
}




TEST(initialDataFlow, Step) {
    //test whether the data was transfered from the init() to simulateStep() 
    init();
    std::vector<std::vector<double>> initialu=u;
    std::vector<std::vector<double>> initialv= v;
    simulateStep();
    //test whether the data transfer from initial to simulation
    bool changed = false;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (u[i][j] != initialu[i][j] || v[i][j] != initialv[i][j]) {
                changed = true;
                break;
            }

        }
        if (changed) break;
    }
    EXPECT_TRUE(changed);


}


TEST(GrayScottDataFlowTest, SimulateStepInternalFlow) {
    //set specific initial status to check whether the dataflow is transfer through simulate function correctly
    u[10][10] = 0.8;
    u[11][10] = 0.7;
    u[9][10] = 0.7;
    u[10][11] = 0.7;
    u[10][9] = 0.7;
    v[10][10] = 0.2;
    v[11][10] = 0.3;
    v[9][10] = 0.3;
    v[10][11] = 0.3;
    v[10][9] = 0.3;
    double original_u = u[10][10];
    double original_v = v[10][10];
    simulateStep();
    double expected_laplace_u = (0.7 + 0.7 + 0.7 + 0.7 - 4 * 0.8);
    double du = u[10][10] - original_u;
    double dv = v[10][10] - original_v;
    EXPECT_TRUE(du != 0.0);
    EXPECT_TRUE(dv != 0.0);
    EXPECT_LT(std::abs(du), dt); 
    EXPECT_LT(std::abs(dv), dt);
}




TEST(Output, writeVTKFile) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            v[x][y] = 0.0;
        }
    }

    //set given initial value rather than random one to test whether the data was transfered from the simulateStep() to  writeVTKFile
    for (int x = 120; x < 130; x++) {
        for (int y = 120; y < 130; y++) {
            v[x][y] = 0.5;  
        }
    }
    std::vector<std::vector<double>> v_copy = v;

    int test_iteration = 999;
    writeVTKFile(test_iteration);

    //test whether the vtk file was created and can be opened
    std::stringstream filename;
    filename << "output_" << test_iteration << ".vtk";
    std::ifstream vtkFile(filename.str());
    ASSERT_TRUE(vtkFile.is_open()) << "Failed to open VTK file";

    //test the head of the vtkfile correct
    std::string line;
    std::vector<std::string> expected_headers = {
        "# vtk DataFile Version 3.0",
        "Gray-Scott Simulation Output",
        "ASCII",
        "DATASET STRUCTURED_POINTS",
        "DIMENSIONS " + std::to_string(width) + " " + std::to_string(height) + " 1",
        "SPACING 1.0 1.0 1.0",
        "ORIGIN 0 0 0",
        "POINT_DATA " + std::to_string(width * height),
        "SCALARS u double",
        "LOOKUP_TABLE default"
    };

    for (const auto& expected : expected_headers) {
        std::getline(vtkFile, line);
        EXPECT_EQ(line, expected) << "Header mismatch";
    }

    // test the file data is correct
    int data_mismatches = 0;
    for (int y = 0; y < height; y++) {
        std::getline(vtkFile, line);
        std::istringstream iss(line);
        for (int x = 0; x < width; x++) {
            double value;
            iss >> value;

            if (std::abs(value - v_copy[x][y]) > 1e-5) {
                data_mismatches++;
                std::cout << "Mismatch at (x,y) = (" << x << "," << y << ")\n";
                std::cout << "Expected: " << v_copy[x][y] << ", Got: " << value << "\n";
            }
        }
    }

    EXPECT_EQ(data_mismatches, 0) << "Found " << data_mismatches << " data mismatches";

    
    bool found_test_pattern = false;
    for (int x = 120; x < 130; x++) {
        for (int y = 120; y < 130; y++) {
            if (std::abs(v_copy[x][y] - 0.5) < 1e-5) {
                found_test_pattern = true;
            }
        }
    }
    EXPECT_TRUE(found_test_pattern) << "Test pattern not found in the expected region";

    vtkFile.close();

    
}



TEST(GrayScottDataFlowTest, ThresholdCountDataFlow) {
    // test the data can go through the countElementsAboveThreshold()
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            v[x][y] = 0.05;  
        }
    }

    for (int x = 100; x < 105; x++) {
        for (int y = 100; y < 105; y++) {
            v[x][y] = 0.2;  
        }
    }

    double threshold = 0.1;
    double ratio = countElementsAboveThreshold(threshold);

    double expected_ratio = 25.0 / (width * height);  
    EXPECT_DOUBLE_EQ(ratio, expected_ratio);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
