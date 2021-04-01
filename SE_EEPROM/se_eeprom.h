/*
	���������� ������������� ��� ������ � EEPROM. ��� ������ ����������� � 3 ����������� ��� ���������� ����������� ��������������� �������������� � ������ ���������� �����������.
	��� ������ � ������� ����������� ������� ������/������ ��������� ������ � ����� ������ �� ����� 32 ��������.
	������ ������������� ��� ������ ������ �� ������ ��������� ����������� ������ EEPROM ����������� �������� �� 3. ���������� ���������� �� �������������� �������� ������� �������������� �����. 
	��� ������� ������ ���������� � ������ ����������� ������� EEPROM.read � EEPROM.write. ��� �� ������� � ���� ������� EEPROM.begin, EEPROM.commit EEPROM.end, ������� ��������� ��������� ������ � ���������� ������ ������������ (NodeMCU).
	
	unsigned short SetEEPROMSize(unsigned short byte_count)
	��������:
		��������� ���������� ���� � �������� � ���������� ����� �������� ��� ������� ������.
	���������:
		byte_count ����� ���� ������ ������� 32 � �� ��������� ������������ ������ EEPROM ����������� �� 3.
		������� ����������� ���� ������ � 3 ���� ����������� byte_count.
	������������ ��������:
		���������� ���� ��� ������.
	
	unsigned short GetEEPROMSize()
	��������:
		��������� ���������� ���� ������������� �������� SetEEPROMSize. 
	������������ ��������:
		���������� ���� ��� ������.
		
  void ClearEEPROMBlock(unsigned short start_index, unsigned short count)
  ��������:
    ��������� ��������� 0 ������ ������ EEPROM. ������������ ��� ��������� ��� ������ ������� EEPROM.
  ���������:
    start_index - ��������� ���� ��� �������. �������� ������ ������������� � ��������� �� 0 �� �������� ������������� GetEEPROMSize()-1.
    count - ���������� ���� ��� �������.
    ����� ��������� ���� start_byte+count ���� ������ GetEEPROMSize()-1
		
	void EEPROMfix()
	��������:
		��������� ������ EEPROM �� ������������. ����������� ���������� ���� 3 ����������� �����. 
		���� ���� �� ��� ���������� �� ��������� 2, ���������� �������������� ������������ ������. 
		���� ��� 3 ���������� ������ ����������, ���� 3 ����������� ������������� �������� 0.

	unsigned char ReadEEPROMByte(unsigned short index)
	��������:
		������ ������ EEPROM �� �������.
	���������:
		index - ������ �����. �������� ������ ������������� � ��������� �� 0 �� �������� ������������� GetEEPROMSize()-1.
	������������ ��������:
		������������ �������� ������. ���� index ������� �� ���������� ������� ��� ������ ����������, ����������� �������� 255.

	bool WriteEEPROMByte(unsigned short index, unsigned char value)
	��������:
		������ �������� � 3 ����������� � EEPROM.
	���������:
		index - ������ �����. �������� ������ ������������� � ��������� �� 0 �� �������� ������������� GetEEPROMSize()-1.
		value - ���� ��� ������
	������������ ��������:
		true � ������ ��������� ���������� ��������, false - ������
		
	String ReadEEPROMStr32(unsigned short start_index)
	��������:
		������ ������ �� EEPROM ������� � ��������� �������. ������ ������ ������������ �� 32 ���� ��� ������� ������������ �������� 0.
	���������:
		start_index - ������ ����� � �������� ������� ������ �����. �������� ������ ������������� � ��������� �� 0 �� �������� ������������� GetEEPROMSize()-1.
	������������ ��������:
		������

	bool WriteEEPROMStr32(unsigned short start_index, String str)
	��������:
		������ ������ � EEPROM � 3 �����������. 
	���������:
		start_index - ������ ����� � �������� ������� ������ ������. �������� ������ ������������� � ��������� �� 0 �� �������� ������������� GetEEPROMSize()-1.
		str - ������ ��� ������
	������������ ��������:
		true � ������ ��������� ���������� ��������, false - ������

	������ ���������� ���������� ����������	Arduino.h � EEPROM.h
	
  Created by Victor S. Bykov, March 31, 2021.
  Released into the public domain.
*/
#ifndef se_eeprom_h
#define se_eeprom_h
#include <Arduino.h>
#include <EEPROM.h>

class SE_EEPROM
{
  public:
		SE_EEPROM(); // ������������� �������
		unsigned short SetEEPROMSize(unsigned short byte_count);
		unsigned short GetEEPROMSize();
		bool ClearEEPROMBlock(unsigned short start_byte, unsigned short count);
		void EEPROMfix();
		unsigned char ReadEEPROMByte(unsigned short index);
		bool WriteEEPROMByte(unsigned short index, unsigned char value);
		String ReadEEPROMStr32(unsigned short index);
		bool WriteEEPROMStr32(unsigned short index, String str);
  private:
		unsigned short eeprom_size;
};
#endif