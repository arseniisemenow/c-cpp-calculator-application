#include "../headers/handle_styles.h"

void setStyleDefaultLineEditExpression(QLineEdit *lineEdit) {
  lineEdit->setStyleSheet(" QLineEdit { \
                                border: 1px solid rgb(100 ,100, 100); /* Border color and width */ \
                                border-radius: 30px; /* Rounded corners */ \
                                padding: 5px; /* Padding inside the QLineEdit */ \
                                background-color: rgb(35,35,35); /* Background color */ \
                                color: rgb(230, 230, 230); /* Text color */ \
                            } \
                             \
                            QLineEdit:focus { \
                                border: 1px solid rgb(147,112,219); /* Border color when QLineEdit is focused */ \
                                background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                            }");
}

void setStyleIncorrectLineEditExpression(QLineEdit *lineEdit) {
  lineEdit->setStyleSheet(" QLineEdit { \
                            border: 1px solid rgb(138, 47, 48); /* Border color and width */ \
                            border-radius: 30px; /* Rounded corners */ \
                            padding: 5px; /* Padding inside the QLineEdit */ \
                            background-color: rgb(35, 35, 35); /* Background color */ \
                            color: rgb(230, 230, 230); /* Text color */ \
                        } \
                         \
                        QLineEdit:focus { \
                            border: 1px solid rgb(207, 66, 68); /* Border color when QLineEdit is focused */ \
                            background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                        }");
}

void setStyleDefaultLineEditVariable(QLineEdit *lineEdit) {
  lineEdit->setStyleSheet("QLineEdit { \
                                border: 1px solid rgb(100 ,100, 100); /* Border color and width */ \
                                border-radius: 10px; /* Rounded corners */ \
                                padding: 1px; /* Padding inside the QLineEdit */ \
                                background-color: rgb(35,35,35); /* Background color */ \
                                color: rgb(230, 230, 230); /* Text color */ \
                                font-size: 10pt; \
                                alignment: center; /* or left, right, justify */ \
                            } \
                             \
                            QLineEdit:focus { \
                                border: 1px solid rgb(147,112,219); /* Border color when QLineEdit is focused */ \
                                background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                            }");
}

void setStyleIncorrectLineEditVariable(QLineEdit *lineEdit) {
  lineEdit->setStyleSheet("QLineEdit { \
                            border: 1px solid rgb(138, 47, 48); /* Border color and width */ \
                            border-radius: 10px; /* Rounded corners */ \
                            padding: 1px; /* Padding inside the QLineEdit */ \
                            background-color: rgb(35,35,35); /* Background color */ \
                            color: rgb(230, 230, 230); /* Text color */ \
                            font-size: 10pt; \
                            alignment: center; /* or left, right, justify */ \
                        } \
                         \
                        QLineEdit:focus { \
                            border: 1px solid rgb(207, 66, 68); /* Border color when QLineEdit is focused */ \
                            background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                        }");
}

void setStyleDefaultLineEditDomains(QLineEdit *lineEdit) {
  lineEdit->setStyleSheet("QLineEdit { \
                                border: 1px solid rgb(100 ,100, 100); /* Border color and width */ \
                                border-radius: 10px; /* Rounded corners */ \
                                padding: 1px; /* Padding inside the QLineEdit */ \
                                background-color: rgb(35,35,35); /* Background color */ \
                                color: rgb(230, 230, 230); /* Text color */ \
                                font-size: 10pt; \
                                alignment: center; /* or left, right, justify */ \
                            } \
                             \
                            QLineEdit:focus { \
                                border: 1px solid rgb(147,112,219); /* Border color when QLineEdit is focused */ \
                                background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                            }");
}

void setStyleIncorrectLineEditDomains(QLineEdit *lineEdit) {
  lineEdit->setStyleSheet("QLineEdit { \
                                border: 1px solid rgb(138, 47, 48); /* Border color and width */ \
                                border-radius: 10px; /* Rounded corners */ \
                                padding: 1px; /* Padding inside the QLineEdit */ \
                                background-color: rgb(35,35,35); /* Background color */ \
                                color: rgb(230, 230, 230); /* Text color */ \
                                font-size: 10pt; \
                                alignment: center; /* or left, right, justify */ \
                            } \
                             \
                            QLineEdit:focus { \
                                border: 1px solid rgb(207, 66, 68); /* Border color when QLineEdit is focused */ \
                                background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                            }");
}

void setStyleDefaultLineEditCredit(QLineEdit *lineEdit) {
  lineEdit->setStyleSheet("QLineEdit { \
                            border: 1px solid rgb(100 ,100, 100); /* Border color and width */ \
                            border-radius: 20px; /* Rounded corners */ \
                            padding: 1px; /* Padding inside the QLineEdit */ \
                            background-color: rgb(35,35,35); /* Background color */ \
                            color: rgb(230, 230, 230); /* Text color */ \
                        } \
                         \
                        QLineEdit:focus { \
                            border: 1px solid rgb(147,112,219); /* Border color when QLineEdit is focused */ \
                            background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                        }");
}

void setStyleIncorrectLineEditCredit(QLineEdit *lineEdit) {
  lineEdit->setStyleSheet("QLineEdit { \
                            border: 1px solid rgb(138, 47, 48); /* Border color and width */ \
                            border-radius: 20px; /* Rounded corners */ \
                            padding: 1px; /* Padding inside the QLineEdit */ \
                            background-color: rgb(35,35,35); /* Background color */ \
                            color: rgb(230, 230, 230); /* Text color */ \
                        } \
                         \
                        QLineEdit:focus { \
                            border: 1px solid rgb(207, 66, 68); /* Border color when QLineEdit is focused */ \
                            background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                        }");
}

void setStyleDefaultLineEditWidget(QLineEdit *lineEdit) {
  lineEdit->setStyleSheet(" \
                                    QLineEdit { \
                                        border: 1px solid rgb(100 ,100, 100); /* Border color and width */ \
                                        border-radius: 7px; /* Rounded corners */ \
                                        padding: 1px; /* Padding inside the QLineEdit */ \
                                        background-color: rgb(35,35,35); /* Background color */ \
                                        color: rgb(230, 230, 230); /* Text color */ \
                                    font-size: 8pt; \
                                    } \
                                     \
                                    QLineEdit:focus { \
                                        border: 1px solid rgb(147,112,219); /* Border color when QLineEdit is focused */ \
                                        background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                                    }");
}

void setStyleIncorrectLineEditWidget(QLineEdit *lineEdit) {
  lineEdit->setStyleSheet(" \
                                    QLineEdit { \
                                        border: 1px solid rgb(138, 47, 48); /* Border color and width */ \
                                        border-radius: 7px; /* Rounded corners */ \
                                        padding: 1px; /* Padding inside the QLineEdit */ \
                                        background-color: rgb(35,35,35); /* Background color */ \
                                        color: rgb(230, 230, 230); /* Text color */ \
                                    font-size: 8pt; \
                                    } \
                                     \
                                    QLineEdit:focus { \
                                        border: 1px solid rgb(207, 66, 68); /* Border color when QLineEdit is focused */ \
                                        background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                                    }");
}

void setStyleDefaultPushButtonWidget(QPushButton *pushButton) {
  pushButton->setStyleSheet("QPushButton { \
                             background-color: rgb(75, 75, 75); /* Background color */ \
                             color: #FFF; /* Text color */ \
                             border: 0px solid #007ACC; /* Border color and width */ \
                             border-radius: 7px; /* Rounded corners */ \
                             padding: 1px; /* Padding inside the button */ \
                         font-size: 11pt; \
                         } \
                          \
                         QPushButton:hover { \
                             background-color: rgb(85, 85, 85); /* Background color on hover */ \
                             border: 1px solid rgb(147,112,219); /* Border color on hover */ \
                         } \
                           \
                         QPushButton:pressed { \
                             background-color: rgb(65, 65, 65); /* Background color when pressed */ \
                             border: 1px solid rgb(147,112,219); /* Border color on hover */ \
                         }");
}
void setStyleIncorrectPushButtonWidget(QPushButton *pushButton) {
  pushButton->setStyleSheet("QPushButton { \
                             background-color: rgb(75, 75, 75); /* Background color */ \
                             color: #FFF; /* Text color */ \
                             border: 1px solid rgb(138, 47, 48); /* Border color and width */ \
                             border-radius: 7px; /* Rounded corners */ \
                             padding: 1px; /* Padding inside the button */ \
                         font-size: 11pt; \
                         } \
                          \
                         QPushButton:hover { \
                             background-color: rgb(85, 85, 85); /* Background color on hover */ \
                             border: 1px solid rgb(147,112,219); /* Border color on hover */ \
                         } \
                           \
                         QPushButton:pressed { \
                             background-color: rgb(65, 65, 65); /* Background color when pressed */ \
                             border: 1px solid rgb(147,112,219); /* Border color on hover */ \
                         }");
}

void setStyleDefaultWidgetComboBox(QComboBox *comboBox) {
  comboBox->setStyleSheet("/* Apply the style to the QComboBox */ \
                            QComboBox { \
                                border: 1px solid rgb(100,100,100); /* Border style and color */ \
                                border-radius: 7px; /* Rounded corners */ \
                                /*padding: 0px ; /* Padding inside the combo box */ \
                                background-color: rgb(35,35,35); /* Background color */ \
                                color: rgb(230,230,230); /* Text color */ \
                                selection-color: #FFF; /* Selected text color */ \
                                selection-background-color: rgb(147,112,219); /* Selected background color */ \
                                font-size: 10pt; \
                            } \
                             \
                            /* Dropdown button style */ \
                            QComboBox::drop-down { \
                                width: 50px;  \
                                border: none; /* Remove the drop-down button border */ \
                                background-color: ; /* Transparent background */ \
                            } \
                             \
                            /* Dropdown list style */ \
                            QComboBox QAbstractItemView { \
                                border: 0px solid #ccc; /* Border style and color for the dropdown list */ \
                                border-radius: 5px; /* Rounded corners for the dropdown list */ \
                                background-color: rgb(35,35,35); /* Background color for the dropdown list */ \
                                color: rgb(230,230,230); /* Text color */ \
                                selection-background-color: rgb(55,55,55); /* Selected item background color */ \
                            } \
                             \
                            /* Hover effect for dropdown list items */ \
                            QComboBox QAbstractItemView::item:hover { \
                                background-color: rgb(147,112,219); /* Background color when hovering over items */ \
                            }");
}

void setStyleDefaultLineEditTransaction(QLineEdit *lineEdit) {
  lineEdit->setStyleSheet(" \
                                    QLineEdit { \
                                        border: 1px solid rgb(100 ,100, 100); /* Border color and width */ \
                                        border-radius: 7px; /* Rounded corners */ \
                                        padding: 1px; /* Padding inside the QLineEdit */ \
                                        background-color: rgb(35,35,35); /* Background color */ \
                                        color: rgb(230, 230, 230); /* Text color */ \
                                    font-size: 8pt; \
                                    } \
                                     \
                                    QLineEdit:focus { \
                                        border: 1px solid rgb(147,112,219); /* Border color when QLineEdit is focused */ \
                                        background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                                    }");
}
void setStyleIncorrectLineEditRefill(QLineEdit *lineEdit) {
  lineEdit->setStyleSheet(" \
                                    QLineEdit { \
                                        border: 1px solid rgb(138, 47, 48); /* Border color and width */ \
                                        border-radius: 7px; /* Rounded corners */ \
                                        padding: 1px; /* Padding inside the QLineEdit */ \
                                        background-color: rgb(35,35,35); /* Background color */ \
                                        color: rgb(230, 230, 230); /* Text color */ \
                                    font-size: 8pt; \
                                    } \
                                     \
                                    QLineEdit:focus { \
                                        border: 1px solid rgb(207, 66, 68); /* Border color when QLineEdit is focused */ \
                                        background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                                    }");
}

void setStyleDefaultDateEditWidget(QDateEdit *dateEdit) {
  dateEdit->setStyleSheet("QDateEdit { \
                            border: 1px solid rgb(100 ,100, 100); /* Border color and width */ \
                            border-radius: 7px; /* Rounded corners */ \
                            padding: 1px; /* Padding inside the QLineEdit */ \
                            background-color: rgb(35,35,35); /* Background color */ \
                            color: rgb(230, 230, 230); /* Text color */ \
                            font-size: 10pt; \
                        } \
                        QDateEdit:focus { \
                            border: 1px solid rgb(147,112,219); /* Border color when QLineEdit is focused */ \
                            background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                        }");
}

void setStyleDefaultLineEditDeposit(QLineEdit *lineEdit) {
  lineEdit->setStyleSheet("    QLineEdit { \
                            border: 1px solid rgb(100 ,100, 100); /* Border color and width */ \
                            border-radius: 10px; /* Rounded corners */ \
                            padding: 1px; /* Padding inside the QLineEdit */ \
                            background-color: rgb(35,35,35); /* Background color */ \
                            color: rgb(200, 200, 200); /* Text color */ \
                        } \
                         \
                        QLineEdit:focus { \
                            border: 1px solid rgb(147,112,219); /* Border color when QLineEdit is focused */ \
                            background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                        }");
}

void setStyleIncorrectLineEditDeposit(QLineEdit *lineEdit) {
  lineEdit->setStyleSheet("    QLineEdit { \
                            border: 1px solid rgb(138, 47, 48); /* Border color and width */ \
                            border-radius: 10px; /* Rounded corners */ \
                            padding: 1px; /* Padding inside the QLineEdit */ \
                            background-color: rgb(35,35,35); /* Background color */ \
                            color: rgb(200, 200, 200); /* Text color */ \
                        } \
                         \
                        QLineEdit:focus { \
                            border: 1px solid rgb(207, 66, 68); /* Border color when QLineEdit is focused */ \
                            background-color: rgb(35, 35, 35); /* Background color when QLineEdit is focused */ \
                        }");
}

void setStyleUnselectedTabButton(QPushButton *button) {
  button->setStyleSheet("QPushButton { \
                                             background-color: rgb(75, 75, 75); /* Background color */ \
                                             color: #FFF; /* Text color */ \
                                             border: 1px solid rgb(100, 100, 100); /* Border color and width */ \
                                             border-radius: 10px; /* Rounded corners */ \
                                             padding: 1px 1px; /* Padding inside the button */ \
                                             font-size: 10pt; \
                                         } \
                                          \
                                         QPushButton:hover { \
                                             background-color: rgb(85, 85, 85); /* Background color on hover */ \
                                             /*border: 2px solid rgb(147,112,219); /* Border color on hover */ \
                                         } \
                                         \
                                         QPushButton:pressed { \
                                             background-color: rgb(65, 65, 65); /* Background color when pressed */ \
                                            /* border: 2px solid rgb(147,112,219); /* Border color on hover */ \
                                         }");
}
void setStyleSelectedTabButton(QPushButton *button) {
  button->setStyleSheet("QPushButton { \
                                             background-color: rgb(75, 75, 75); /* Background color */ \
                                             color: #FFF; /* Text color */ \
                                             border: 1px solid rgb(147,112,219); /* Border color and width */ \
                                             border-radius: 10px; /* Rounded corners */ \
                                             padding: 1px 1px; /* Padding inside the button */ \
                                             font-size: 10pt; \
                                         } \
                                          \
                                         QPushButton:hover { \
                                             background-color: rgb(85, 85, 85); /* Background color on hover */ \
                                             /*border: 2px solid rgb(147,112,219); /* Border color on hover */ \
                                         } \
                                         \
                                         QPushButton:pressed { \
                                             background-color: rgb(65, 65, 65); /* Background color when pressed */ \
                                            /* border: 2px solid rgb(147,112,219); /* Border color on hover */ \
                                         }");
}
