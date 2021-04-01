#include "se_eeprom.h"

SE_EEPROM::SE_EEPROM()
{
  eeprom_size=0;
};

/*
  unsigned short SetEEPROMSize(unsigned short byte_count)
  ��������:
    ��������� ���������� ���� � �������� � ���������� ����� �������� ��� ������� ������.
  ���������:
    byte_count ����� ���� ������ ������� 32 � �� ��������� ������������ ������ EEPROM ����������� �� 3.
    ������� ����������� ���� ������ � 3 ���� ����������� byte_count.
  ������������ ��������:
    ���������� ���� ��� ������.
*/    
unsigned short SE_EEPROM::SetEEPROMSize(unsigned short byte_count)
{
  unsigned short tmp;
  tmp=byte_count/32;
  tmp=tmp*32;
  eeprom_size=tmp;
  Serial.println();
  return tmp;
};

/*
  unsigned short GetEEPROMSize()
  ��������:
    ��������� ���������� ���� ������������� �������� SetEEPROMSize. 
  ������������ ��������:
    ���������� ���� ��� ������.
*/    
unsigned short SE_EEPROM::GetEEPROMSize()
{
  return eeprom_size; 
};

/*
  bool ClearEEPROMBlock(unsigned short start_index, unsigned short count)
  ��������:
    ��������� ��������� 0 ������ ������ EEPROM. ������������ ��� ��������� ��� ������ ������� EEPROM.
  ���������:
    start_index - ��������� ���� ��� �������. �������� ������ ������������� � ��������� �� 0 �� �������� ������������� GetEEPROMSize()-1.
    count - ���������� ���� ��� �������.
    ����� ��������� ���� start_index+count ���� ������ GetEEPROMSize()-1
*/
bool SE_EEPROM::ClearEEPROMBlock(unsigned short start_index, unsigned short count)
{
  unsigned short i,j;
  if (start_index>=eeprom_size) return false; // ���� ����������� � ������� ������, ��� ����
  j=count;
  if (start_index+count>eeprom_size)
    j=eeprom_size-start_index;

  i=start_index;
  while (i<j)
  {
    WriteEEPROMByte(i, 0);
    i++;
  }
  return true;
};  

/*
  void EEPROMfix()
  ��������:
    ��������� ������ EEPROM �� ������������. ����������� ���������� ���� 3 ����������� �����. 
    ���� ���� �� ��� ���������� �� ��������� 2, ���������� �������������� ������������ ������. 
    ���� ��� 3 ���������� ������ ����������, ���� 3 ����������� ������������� �������� 0.
*/    
void SE_EEPROM::EEPROMfix()
{
  unsigned short i;
  unsigned char res_0, res_1, res_2, total_res;
 
  for (int i=0;i<eeprom_size;i++)
  {
    res_0=EEPROM.read(i*3);
    res_1=EEPROM.read(i*3+1);  
    res_2=EEPROM.read(i*3+2);
    if ((res_0==res_1) && (res_1==res_2)) continue;
    if (res_0==res_1) {EEPROM.write(i*3+2,res_0); continue;}
    if (res_0==res_2) {EEPROM.write(i*3+1,res_0);continue;}
    if (res_1==res_2) {EEPROM.write(i*3+2,res_1);continue;}
    // ���� ��� 3 �������� ������
    EEPROM.write(i*3,0);
    EEPROM.write(i*3+1,0);
    EEPROM.write(i*3+2,0);
  }
};

/*
  unsigned char ReadEEPROMByte(unsigned short index)
  ��������:
    ������ ������ EEPROM �� �������.
  ���������:
    index - ������ �����. �������� ������ ������������� � ��������� �� 0 �� �������� ������������� GetEEPROMSize()-1.
  ������������ ��������:
    ������������ �������� ������. ���� index ������� �� ���������� �������, ����������� �������� 255.
*/    
unsigned char SE_EEPROM::ReadEEPROMByte(unsigned short index)
{
  unsigned char res_0, res_1, res_2, total_res;

  if (index>=eeprom_size) return 255; // ���� ����������� � ������� ������, ��� ����

  res_0=EEPROM.read(index*3);
  res_1=EEPROM.read(index*3+1);  
  res_2=EEPROM.read(index*3+2);

  if (res_0==res_1) return res_0;
  if (res_0==res_2) return res_0;
  if (res_1==res_2) return res_1;
  return 255;
};

/*
  bool WriteEEPROMByte(unsigned short index, unsigned char value)
  ��������:
    ������ �������� � 3 ����������� � EEPROM.
  ���������:
    index - ������ �����. �������� ������ ������������� � ��������� �� 0 �� �������� ������������� GetEEPROMSize()-1.
    value - ���� ��� ������
  ������������ ��������:
    true � ������ ��������� ���������� ��������, false - ������
*/
bool SE_EEPROM::WriteEEPROMByte(unsigned short index, unsigned char value)
{
  if (index>=eeprom_size) return false;
  if (ReadEEPROMByte(index)==value) return true;

  EEPROM.write(index*3,value);
  EEPROM.write(index*3+1,value);
  EEPROM.write(index*3+2,value);
  return true;
};

/*
  String ReadEEPROMStr32(unsigned short start_index)
  ��������:
    ������ ������ �� EEPROM ������� � ��������� �������. ������ ������ ������������ �� 32 ���� ��� ������� ������������ �������� 0.
  ���������:
    index - ������ ����� � �������� ������� ������ �����. �������� ������ ������������� � ��������� �� 0 �� �������� ������������� GetEEPROMSize()-1.
  ������������ ��������:
    ������
*/
String SE_EEPROM::ReadEEPROMStr32(unsigned short start_index)
{
  unsigned short i;
  char ch;
  String res="";
  if (start_index>=eeprom_size) return res; // ���� ����������� � ������� ������, ��� ����

	for (i=0;i<32;i++)
	{
		if (start_index+i>=eeprom_size) break;
    ch=ReadEEPROMByte(i);
    if (ch!=0)
      res=res+ch;
    else
      break;		
	}	
  return res; 
};

/*
  bool WriteEEPROMStr32(unsigned short start_index, String str)
  ��������:
    ������ ������ � EEPROM � 3 �����������. 
  ���������:
    start_index - ������ ����� � �������� ������� ������ ������. �������� ������ ������������� � ��������� �� 0 �� �������� ������������� GetEEPROMSize()-1.
    value - ������ ��� ������
  ������������ ��������:
    true � ������ ��������� ���������� ��������, false - ������

*/
bool SE_EEPROM::WriteEEPROMStr32(unsigned short start_index, String str)
{
  unsigned short i,len;
  if (start_index>=eeprom_size) return false; // ���� ����������� � ������� ������, ��� ����
	len=str.length();
	for (i=0;i<32;i++)
	{
		if (start_index+i>=eeprom_size) break;
		if (i<len)
			WriteEEPROMByte(start_index+i,str[i]);
		else
		{
			WriteEEPROMByte(start_index+i,0);		
			break;
		}
	}
  return true;  
};