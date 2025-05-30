cmake_minimum_required(VERSION 3.19)
project(BookingApp LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(BookingApp
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    mainmenuwindow.h mainmenuwindow.cpp mainmenuwindow.ui
    utilities.h
    utilities.cpp
    datasource.h
    datasource.cpp
    config.json
    user.h
    user.cpp
    room.h
    room.cpp
    roomtype.h
    roomtype.cpp
    booking.h
    booking.cpp
    dialogroomlist.h dialogroomlist.cpp dialogroomlist.ui
    globals.h
    globals.cpp
    dialogbookingadd.h dialogbookingadd.cpp dialogbookingadd.ui
    dialogbookinglisttoday.h dialogbookinglisttoday.cpp dialogbookinglisttoday.ui
    dialogbookinglistweek.h dialogbookinglistweek.cpp dialogbookinglistweek.ui
    dialogbookinglistmonthly.h dialogbookinglistmonthly.cpp dialogbookinglistmonthly.ui
    dialogbookingupdate.h dialogbookingupdate.cpp dialogbookingupdate.ui
    dialogbookingcancel.h dialogbookingcancel.cpp dialogbookingcancel.ui



)



qt_add_translations(
    TARGETS BookingApp
    TS_FILES BookingApp_en_AU.ts
)

target_link_libraries(BookingApp
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS BookingApp
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET BookingApp
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
