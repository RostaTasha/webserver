cmake_minimum_required(VERSION 2.8)	 # Проверка версии CMake.
										# Если версия установленой программы
										# старее указаной, произайдёт аварийный выход.

										
add_definitions(-std=c++11)							
										
project(final)			# Название проекта

set(SOURCE_EXE main.cpp)		# Установка переменной со списком исходников для исполняемого файла


add_executable(final ${SOURCE_EXE})	# Создает исполняемый файл с именем final

target_link_libraries(final pthread)		# Линковка программы с библиотекой