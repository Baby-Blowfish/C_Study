// �ڷ����� ���� : -2^(��Ʈ��-1) ~ 2^(��Ʈ�� -1)-1
//         char : -128 ~ 127
/*    ������ �ڷ���
      char : 1byte            %c, %d
      short : 2byte           %d
      int : 4byte             %d
      long : 4byte            %ld
      long long : 8byte       %lld
      unsigned char : 1byte            %u
      unsigned short : 2byte           %u
      unsigned int : 4byte             %u
      unsigned long : 4byte            %lu
      unsigned long long : 8byte       %llu
*/
// unsigned �ڷ����� �� �� �׻� ����� �����ϰ� %u�� ����Ѵ�!

/*    �Ǽ��� �ڷ���
      float :4byte          ��ȿ���� : 7            %f
      double : 8byte        ��ȿ���� : 15           %lf
      long double : 8byte   ��ȿ���� : 15�̻�       %Lf

*/

/*    ���ڿ�
      char �迭��[���ڿ����� +1] = ���ڿ�;
      �����Ϸ��� ���ڿ��� ���� �ι���('\0')�� �ڵ����� �߰�
*/

/*    const Ű����
      const �ڷ��� ������ = ��;
      const�� ������ �ʱ�ȭ �ÿ��� ��밡���ϴ�.
      const�� ����� ������ �ʱ�ȭ�� ���� �ٲ� �� ����.
*/

/*    �����(reserved word, key word)�� �ĺ���(identifier)

*/

#include<stdio.h>
#include<string.h>

int main(void)
{
  char fruit[20] = "strawberry";
  strcpy(fruit,"banana");
  printf("%s",fruit);

  return 0;
}