#include <gtest/gtest.h>
#include "gs.h"  

TEST(SimulationTest, InitializationTest) {
    init();
    EXPECT_NEAR(countElementsAboveThreshold(0.5), 0.0, 0.1);
}

TEST(SimulationTest, SimulateStepTest) {
    init();
    double initialCount = countElementsAboveThreshold(0.1);
    simulateStep();
    double updatedCount = countElementsAboveThreshold(0.1);
    EXPECT_NE(initialCount, updatedCount); 
}

TEST(SimulationTest, ThresholdCountTest) {
    init();
    
    double original_threshold = threshold;  
    threshold = 0.5;
    double count = countElementsAboveThreshold(threshold);
    EXPECT_GE(count, 0.0);  
    threshold = original_threshold;  
}

TEST(ExtremeParameterTest, HighAndLowParameters) {
    std::srand(42);
    init();  

    double Du_high = 1.0, Du_low = 0.001;
    double Dv_high = 1.0, Dv_low = 0.001;
    double F_high = 0.1, F_low = 0.0;
    double k_high = 0.1, k_low = 0.0;

    Du = Du_high;
    Dv = Dv_high;
    F = F_high;
    k = k_high;
    simulateStep();
    EXPECT_NO_THROW(simulateStep());  

    Du = Du_low;
    Dv = Dv_low;
    F = F_low;
    k = k_low;
    simulateStep();
    EXPECT_NO_THROW(simulateStep());  
}
