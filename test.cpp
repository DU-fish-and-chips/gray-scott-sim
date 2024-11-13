#include "gs.h"  // 假设 gs.h 是声明变量和函数的头文件

#include <typeinfo>

// 测试 F 和 k 的类型是否与 u 和 v 的元素类型匹配
TEST(ModelParameterTypeTest, CheckTypeMatch) {
    // 检查 F 的类型是否与 u 的元素类型一致
    EXPECT_EQ(typeid(F), typeid(u[0][0])) << "Type of F does not match type of u elements";

    // 检查 k 的类型是否与 v 的元素类型一致
    EXPECT_EQ(typeid(k), typeid(v[0][0])) << "Type of k does not match type of v elements";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
