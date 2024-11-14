#include "gs.h"
#include <tuple>
#include <gtest/gtest.h>

// 1.1 Long-term Stability Test
TEST(GrayScottTest, ExtendedStabilityTest) {
    init();
    const int extendedSteps = 10000;
    for (int i = 0; i < extendedSteps; ++i) {
        simulateStep();
    }
    bool isStable = true;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (u[x][y] < 0.0 || u[x][y] > 1.0 || v[x][y] < 0.0 || v[x][y] > 1.0) {
                isStable = false;
                break;
            }
        }
        if (!isStable) break;
    }
    EXPECT_TRUE(isStable);
}

// 1.2 Parameter Sensitivity Test
TEST(GrayScottTest, ParameterSensitivityTest) {
    std::vector<std::tuple<double, double>> testParams = {
        {0.03, 0.06},
        {0.03, 0.07},
        {0.04, 0.06},
        {0.04, 0.07}
    };
    for (auto& [testF, testK] : testParams) {
        F = testF;
        k = testK;
        init();
        const int steps = 1000;
        bool isStable = true;
        for (int i = 0; i < steps; ++i) {
            simulateStep();
        }
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                if (u[x][y] < 0.0 || u[x][y] > 1.0 || v[x][y] < 0.0 || v[x][y] > 1.0) {
                    isStable = false;
                    break;
                }
            }
            if (!isStable) break;
        }
        EXPECT_TRUE(isStable) << "Failed for F=" << testF << " and k=" << testK;
    }
}

// 1.3 Boundary Stability Test
TEST(GrayScottTest, BoundaryStabilityTest) {
    init();
    const int steps = 5000;
    for (int i = 0; i < steps; ++i) {
        simulateStep();
    }
    bool isBoundaryStable = true;
    for (int x = 0; x < width; ++x) {
        if (u[x][0] < 0.0 || u[x][0] > 1.0 || v[x][0] < 0.0 || v[x][0] > 1.0 ||
            u[x][height - 1] < 0.0 || u[x][height - 1] > 1.0 || v[x][height - 1] < 0.0 || v[x][height - 1] > 1.0) {
            isBoundaryStable = false;
            break;
        }
    }
    for (int y = 0; y < height; ++y) {
        if (u[0][y] < 0.0 || u[0][y] > 1.0 || v[0][y] < 0.0 || v[0][y] > 1.0 ||
            u[width - 1][y] < 0.0 || u[width - 1][y] > 1.0 || v[width - 1][y] < 0.0 || v[width - 1][y] > 1.0) {
            isBoundaryStable = false;
            break;
        }
    }
    EXPECT_TRUE(isBoundaryStable);
}

// 1.4 Time Step Sensitivity Test
TEST(GrayScottTest, TimeStepSensitivityTest) {
    std::vector<double> timeSteps = { 0.02, 0.04, 0.06, 0.08 };
    for (double testDt : timeSteps) {
        double originalDt = dt;
#undef dt
        double dt = testDt;
        init();
        const int steps = 1000;
        bool isStable = true;
        for (int i = 0; i < steps; ++i) {
            simulateStep();
        }
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                if (u[x][y] < 0.0 || u[x][y] > 1.0 || v[x][y] < 0.0 || v[x][y] > 1.0) {
                    isStable = false;
                    break;
                }
            }
            if (!isStable) break;
        }
#define dt originalDt
        EXPECT_TRUE(isStable) << "Failed for dt=" << testDt;
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
