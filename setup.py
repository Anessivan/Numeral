import pybind11
from setuptools._distutils.core import setup, Extension

ext_modules = [
    Extension(
        'rungekutta4', # имя библиотеки собранной pybind11
        ['Source.cpp'], # Тестовый файлик который компилируем
        include_dirs=[pybind11.get_include()],  # не забываем добавить инклюды pybind11
        language='c++', # Указываем язык
        extra_compile_args=['-std=c++14'], # флаг с++11
        extra_link_args=[]
    ),
]

setup(
    name='rungekutta4', # имя библиотеки собранной pybind11
    version='1.0.0',
    author='Anessivan',
    author_email='dmitry_rostov@list.ru',
    description='numerical methods extension',
    ext_modules=ext_modules,
    requires=['pybind11'],  # Указываем зависимость от pybind11
    #package_dir = {'': 'lib'}
)
