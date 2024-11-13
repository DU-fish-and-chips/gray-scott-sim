#include "gs.h"  // ���� gs.h �����������ͺ�����ͷ�ļ�

#include <typeinfo>

// ���� F �� k �������Ƿ��� u �� v ��Ԫ������ƥ��
TEST(ModelParameterTypeTest, CheckTypeMatch) {
    // ��� F �������Ƿ��� u ��Ԫ������һ��
    EXPECT_EQ(typeid(F), typeid(u[0][0])) << "Type of F does not match type of u elements";

    // ��� k �������Ƿ��� v ��Ԫ������һ��
    EXPECT_EQ(typeid(k), typeid(v[0][0])) << "Type of k does not match type of v elements";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
