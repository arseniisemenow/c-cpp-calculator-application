QT       += core gui widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

CONFIG += c++17

INCLUDEPATH += "qcustomplot_lib"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../common/s21_aux_funcs.c \
    custom_widgets/InterestRateWidget.cpp \
    custom_widgets/PartialWithdrawalsWidget.cpp \
    custom_widgets/RefillsWidget.cpp \
    custom_widgets/TransactionWidget.cpp \
    sources/calculate_plot.cpp \
    ../credit_calculator_backend/functions/s21_credit.c \
    ../deposit_calculator_backend/functions/s21_deposit.c \
    ../deposit_calculator_backend/functions/s21_deposit_api.c \
    ../deposit_calculator_backend/functions/s21_log.c \
    ../deposit_calculator_backend/functions/s21_quick_sort.c \
    ../deposit_calculator_backend/functions/s21_taxes.c \
    ../deposit_calculator_backend/functions/s21_transaction_list.c \
    ../deposit_calculator_backend/functions/s21_transactions.c \
    ../develop/s21_develop.c \
    sources/error_code_to_error_string.cpp \
    sources/handle_format_calculations_result.cpp \
    sources/handle_output_last_calculations.cpp \
    sources/handle_styles.cpp \
    sources/handle_tab_switch.cpp \
    main.cpp \
    sources/MainWindow.cpp \
    sources/parsing_helpers.cpp \
    qcustomplot_lib/qcustomplot.cpp \
    sources/set_current_date.cpp \
    sources/string_processing_functions.cpp \
    sources/string_validator.cpp

SOURCES += \
    ../expression_calculator_backend/functions/calculation/s21_calculation.c \
    ../expression_calculator_backend/functions/calculation/s21_calculation_handlers.c \
    ../expression_calculator_backend/functions/calculation_library/s21_calc_library.c \
    ../expression_calculator_backend/functions/expression_tokenizer/s21_expression_tokenizer.c \
    ../expression_calculator_backend/functions/expression_tokenizer/s21_validator.c \
    ../expression_calculator_backend/functions/shunting_yard_algorithm/s21_shunting_yard_algorithm.c \
    ../expression_calculator_backend/functions/stack/s21_stack.c \

HEADERS += \
    custom_widgets/InterestRateWidget.h \
    custom_widgets/PartialWithdrawalsWidget.h \
    custom_widgets/RefillsWidget.h \
    custom_widgets/TransactionWidget.h \
    headers/calculate_plot.h \
    ../common/headers/s21_common_libs.h \
    ../common/headers/s21_common_structs.h \
    ../credit_calculator_backend/headers/s21_credit.h \
    ../credit_calculator_backend/headers/s21_credit_calc_library.h \
    ../credit_calculator_backend/headers/s21_credit_structs.h \
    ../deposit_calculator_backend/headers/s21_deposit.h \
    ../deposit_calculator_backend/headers/s21_deposit_api.h \
    ../deposit_calculator_backend/headers/s21_deposit_calc_library.h \
    ../deposit_calculator_backend/headers/s21_deposit_structs.h \
    ../deposit_calculator_backend/headers/s21_log.h \
    ../deposit_calculator_backend/headers/s21_quick_sort.h \
    ../deposit_calculator_backend/headers/s21_taxes.h \
    ../deposit_calculator_backend/headers/s21_transaction_list.h \
    ../deposit_calculator_backend/headers/s21_transactions.h \
    ../develop/s21_develop.h \
    headers/cross_platform_differences.h \
    headers/error_code_to_error_string.h \
    ../expression_calculator_backend/headers/s21_calc_library.h \
    ../expression_calculator_backend/headers/s21_calculation.h \
    ../expression_calculator_backend/headers/s21_calculation_handlers.h \
    ../expression_calculator_backend/headers/s21_expression_tokenizer.h \
    ../expression_calculator_backend/headers/s21_libs.h \
    ../expression_calculator_backend/headers/s21_shunting_yard_algorithm.h \
    ../expression_calculator_backend/headers/s21_stack.h \
    ../expression_calculator_backend/headers/s21_structs.h \
    ../expression_calculator_backend/headers/s21_validator.h \
    headers/front_error_codes.h \
    headers/handle_format_calculations_result.h \
    headers/handle_output_last_calculations.h \
    headers/handle_styles.h \
    headers/handle_tab_switch.h \
    headers/parsing_helpers.h \
    qcustomplot_lib/qcustomplot.h \
    headers/MainWindow.h \
    headers/set_current_date.h \
    headers/Settings.h \
    headers/string_processing_functions.h \
    headers/string_validator.h

FORMS += \
    ui/mainwindow.ui




QMAKE_EXTRA_TARGETS += format

format.target = format
format.commands = \
    echo "Start formatting..."; \
    clang-format -i *.c *.h *.cpp; \
    clang-format -i ../*/*.c ../*/*.h ../*/*.cpp; \
    clang-format -i ../*/*/*.c ../*/*/*.h ../*/*/*.cpp; \
    clang-format -i ../*/*/*/*.c ../*/*/*/*.h ../*/*/*/*.cpp; \
    clang-format -i ../*/*/*/*/*.c ../*/*/*/*/*.h ../*/*/*/*/*.cpp; \
    clang-format -i ../*/*/*/*/*/*.c ../*/*/*/*/*/*.h ../*/*/*/*/*/*.cpp; \
    echo "Formatting complete.";

format.depends = FORCE

PRE_TARGETDEPS += format
FORCE:



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

