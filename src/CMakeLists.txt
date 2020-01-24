
find_package(Qt5 COMPONENTS Widgets Script REQUIRED)

set(SOURCE_FILES
    GeenSyntaxHighlighter.cpp
    GeenTextEditor.cpp
    MainWindow.cpp
    main.cpp
)

set(HEADER_FILES
    GeenSyntaxHighlighter.h
    GeenTextEditor.h
    MainWindow.h
)

set(UI_FILES
    MainWindow.ui
)

set(RESOURCE_FILES
    iconresource.qrc
)

add_executable(geen
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${UI_FILES}
    ${RESOURCE_FILES}
)

target_link_libraries(geen
    Qt5::Script
    Qt5::Widgets
)
