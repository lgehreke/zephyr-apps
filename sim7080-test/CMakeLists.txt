# Copyrigth (C) 2021 metraTec GmbH

cmake_minimum_required(VERSION 3.10.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(sim7080_test)

zephyr_library_compile_options(-Wall -Werror)

target_sources(app PRIVATE src/main.c)
