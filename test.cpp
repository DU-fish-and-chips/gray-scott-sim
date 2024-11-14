#include "gs.h"  ///< ���� gs.h �����������ͺ�����ͷ�ļ�

#include <typeinfo>

/**
 * @brief ����ģ�Ͳ��� F �� k �������Ƿ������� u �� v ��Ԫ������ƥ�䡣
 *
 * ������Լ�� F �������Ƿ��� u �����Ԫ������һ�£�
 * �Լ� k �������Ƿ��� v �����Ԫ������һ�¡�
 */
TEST(ModelParameterTypeTest, CheckTypeMatch) {
    /**
     * @brief ��� F �������Ƿ��� u ��Ԫ������һ�¡�
     * @note ������Ͳ�ƥ�䣬�����������Ϣ��
     */
    EXPECT_EQ(typeid(F), typeid(u[0][0])) << "Type of F does not match type of u elements";

    /**
     * @brief ��� k �������Ƿ��� v ��Ԫ������һ�¡�
     * @note ������Ͳ�ƥ�䣬�����������Ϣ��
     */
    EXPECT_EQ(typeid(k), typeid(v[0][0])) << "Type of k does not match type of v elements";
}

/**
 * @brief ����������ʼ�� GoogleTest ���������в��ԡ�
 *
 * @param argc �����в�����������
 * @param argv �����в��������顣
 * @return GoogleTest ִ�еĽ�����롣
 */
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
