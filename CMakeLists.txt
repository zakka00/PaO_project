cmake_minimum_required(VERSION 3.16)
project(ecommerce)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 👉 PRIMA crei il target
add_executable(ecommerce
    # CPP
    Sources/main.cpp
    Sources/Graphics/Filters.cpp
    Sources/Graphics/Homepage.cpp
    Sources/Graphics/SingleProductCreation.cpp
    Sources/Graphics/SingleProductEdit.cpp
    Sources/Graphics/Miniature.cpp
    Sources/Graphics/ProductsView.cpp
    Sources/Graphics/SingleProduct.cpp
    Sources/Logic/Clothing.cpp
    Sources/Logic/Electronics.cpp
    Sources/Logic/PrintedMedia.cpp
    Sources/Logic/Product.cpp
    Sources/Logic/Store.cpp
    Sources/Logic/Visitors/ProductEditorVisitor.cpp
    Sources/Logic/Visitors/ProductIconVisitor.cpp
    Sources/Logic/Visitors/ProductSingleProductVisitor.cpp

    # 🔥 AGGIUNGI QUESTI (FONDAMENTALE)
    Headers/Graphics/Filters.h
    Headers/Graphics/Homepage.h
    Headers/Graphics/SingleProductCreation.h
    Headers/Graphics/SingleProductEdit.h
    Headers/Graphics/Miniature.h
    Headers/Graphics/ProductsView.h
    Headers/Graphics/SingleProduct.h

    resources.qrc
)

# 👉 POI include
target_include_directories(ecommerce PRIVATE
    Headers
    Headers/Graphics
    Headers/Logic
    Headers/Logic/Visitors
)

# 👉 POI link
target_link_libraries(ecommerce PRIVATE Qt6::Widgets)