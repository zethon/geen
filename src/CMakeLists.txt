
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

if (WIN32)
    set(EXTRA_RESOURCES
        geen.rc
    )
endif(WIN32)

add_executable(geen
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${UI_FILES}
    ${RESOURCE_FILES}
    ${EXTRA_RESOURCES}
)

find_package(Qt5 REQUIRED COMPONENTS
    Qml
    Widgets
)

target_link_libraries(geen
    Qt5::Qml
    Qt5::Widgets
)

