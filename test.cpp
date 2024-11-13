#include "gs.h"  ///< 假设 gs.h 是声明变量和函数的头文件

#include <typeinfo>

/**
 * @brief 测试模型参数 F 和 k 的类型是否与数组 u 和 v 的元素类型匹配。
 *
 * 这个测试检查 F 的类型是否与 u 数组的元素类型一致，
 * 以及 k 的类型是否与 v 数组的元素类型一致。
 */
TEST(ModelParameterTypeTest, CheckTypeMatch) {
    /**
     * @brief 检查 F 的类型是否与 u 的元素类型一致。
     * @note 如果类型不匹配，则输出错误信息。
     */
    EXPECT_EQ(typeid(F), typeid(u[0][0])) << "Type of F does not match type of u elements";

    /**
     * @brief 检查 k 的类型是否与 v 的元素类型一致。
     * @note 如果类型不匹配，则输出错误信息。
     */
    EXPECT_EQ(typeid(k), typeid(v[0][0])) << "Type of k does not match type of v elements";
}

/**
 * @brief 主函数，初始化 GoogleTest 并运行所有测试。
 *
 * @param argc 命令行参数的数量。
 * @param argv 命令行参数的数组。
 * @return GoogleTest 执行的结果代码。
 */
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
