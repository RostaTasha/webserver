cmake_minimum_required(VERSION 2.8)	 # �������� ������ CMake.
										# ���� ������ ������������ ���������
										# ������ ��������, ��������� ��������� �����.

										
add_definitions(-std=c++11)							
										
project(final)			# �������� �������

set(SOURCE_EXE main.cpp)		# ��������� ���������� �� ������� ���������� ��� ������������ �����


add_executable(final ${SOURCE_EXE})	# ������� ����������� ���� � ������ final

target_link_libraries(final pthread)		# �������� ��������� � �����������