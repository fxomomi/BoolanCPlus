#include "NewAndDelete.h"

int main() {

	// Fruit
	cout << "===============" << setw(15) << setiosflags(ios::left) << " Fruit Begin" << "===============" << endl;
	Fruit* pFruit = new Fruit();
	delete pFruit;
	Fruit* pArrFruit = new Fruit[3]();
	delete[] pArrFruit;
	cout << "===============" << setw(15) << " Fruit End" << "===============" << endl << endl;

	// Apple
	cout << "===============" << setw(15) << " Apple Begin" << "===============" << endl;
	Apple* pApple = new Apple();
	delete pApple;
	Apple* pArrApple = new Apple[3]();
	delete[] pArrApple;
	cout << "===============" << setw(15) << " Apple End" << "===============" << endl << endl;

	// ::opeartor new & ::opeartor delete
	cout << "=============== Global opeartor Begin ===============" << endl;
	Apple* pgApple = ::new Apple();
	::delete pgApple;
	Apple* pgArryApple = ::new Apple[3]();
	::delete[] pgArryApple;
	cout << "=============== Global opeartor End ===============" << endl;

	getchar();
	return 0;
}

/*
=============== Fruit Begin   ===============
Global::opeartor new(). size=32
Fruit::ctor. this=030AADE0 no=1
Fruir::dtor. this=030AADE0 no=1
Global::opeartor delete(). pdead: 030AADE0 size=32
Global::opeartor new[](). size=100
Fruit::ctor. this=030A52D4 no=1
Fruit::ctor. this=030A52F4 no=2
Fruit::ctor. this=030A5314 no=3
Fruir::dtor. this=030A5314 no=3
Fruir::dtor. this=030A52F4 no=2
Fruir::dtor. this=030A52D4 no=1
Global::opeartor delete[](). pdead: 030A52D0 size=100
=============== Fruit End     ===============
������
1��Furit ��û������ member operator new,new[],delete,delete[] ��˵��õ���ȫ�ְ汾��
2��ʹ�� new ����һ�� Fruit ����ʱ������ 32 �ֽڵ��ڴ棬����һ�ڷ���һ�£����а���һ�� 8 �ֽڵ���ָ�롢int no 4+4��double weight 8�� char key 1+7
3���������ʱ�������ڴ棬����ù��캯������������ʱ�ȵ����������������ͷ��ڴ档
4��ʹ�� new[] ���칹��3�� Fruit ����ʱ������ 100 �ֽڵ��ڴ棬���� 96 �ֽ�Ϊ 3 �� Fruit �Ĵ�С����������ֽ����ڴ�������С
5�������еĶ����ȹ���ĺ����������������������������ʾ no=3 �Ķ������Ź��죬������������

=============== Apple Begin   ===============
Apple::opeartor new. size=40 return: 030AADE0
Fruit::ctor. this=030AADE0 no=1
Apple::ctor. this=030AADE0
Apple::dtor. this=030AADE0
Fruir::dtor. this=030AADE0 no=1
Apple::opeartor delete. pdead: 030AADE0 size=40
Apple::opeartor new[]. size=124 return: 030AA1B0
Fruit::ctor. this=030AA1B4 no=1
Apple::ctor. this=030AA1B4
Fruit::ctor. this=030AA1DC no=2
Apple::ctor. this=030AA1DC
Fruit::ctor. this=030AA204 no=3
Apple::ctor. this=030AA204
Apple::dtor. this=030AA204
Fruir::dtor. this=030AA204 no=3
Apple::dtor. this=030AA1DC
Fruir::dtor. this=030AA1DC no=2
Apple::dtor. this=030AA1B4
Fruir::dtor. this=030AA1B4 no=1
Apple::opeartor delete[]. pdead: 030AA1B0 size=124
=============== Apple End     ===============
������
1��Furit �������� member operator new,new[],delete,delete[] ��˵��õ��� class member �İ汾
2��ʹ�� new ����һ�� Apple ����ʱ������ 40 �ֽڵ��ڴ棬����һ�ڷ���һ�£����а���һ�� 8 �ֽڵ���ָ�롢int no 4+4��double weight 8�� char key + int size 1+7, char type 1+7
3������ Apple ����ʱ���ȵ��ø��� Fruit �Ĺ��캯������βŵ��� Apple �Ĺ��캯����
4������ Apple ����ʱ���ȵ��� Apple �Լ���������������βŵ��ø��� Fruit ������������
5��ʹ�� new[] ���칹��3�� Apple ����ʱ������ 124 �ֽڵ��ڴ棬���� 120 �ֽ�Ϊ 3 �� Fruit �Ĵ�С����������ֽ����ڴ�������С��
6�������еĶ����ȹ���ĺ����������������������������ʾ no=3 �Ķ������Ź��죬����������������ÿ������ʱ�ȸ��������࣬����ʱ�������ٸ��ࡣ

=============== Global opeartor Begin ===============
Global::opeartor new(). size=40
Fruit::ctor. this=030AADE0 no=1
Apple::ctor. this=030AADE0
Apple::dtor. this=030AADE0
Fruir::dtor. this=030AADE0 no=1
Global::opeartor delete(). pdead: 030AADE0 size=40
Global::opeartor new[](). size=124
Fruit::ctor. this=030AA1B4 no=1
Apple::ctor. this=030AA1B4
Fruit::ctor. this=030AA1DC no=2
Apple::ctor. this=030AA1DC
Fruit::ctor. this=030AA204 no=3
Apple::ctor. this=030AA204
Apple::dtor. this=030AA204
Fruir::dtor. this=030AA204 no=3
Apple::dtor. this=030AA1DC
Fruir::dtor. this=030AA1DC no=2
Apple::dtor. this=030AA1B4
Fruir::dtor. this=030AA1B4 no=1
Global::opeartor delete[](). pdead: 030AA1B0 size=124
=============== Global opeartor End ===============
������
1���˴����� ::new��::new[]��::delete �� ::delete[] ��������ɾ������ǿ�Ƶ����� Global �İ汾��
2�����˵��õ��� Global �汾�� new �� delete �����⣬���������������ͬ��
*/