add_library(spielewiese STATIC
            include/spielewiese/Optional.hpp
            include/spielewiese/Result.hpp
            NotUsedYet.cpp
)

target_include_directories(spielewiese
                           PUBLIC include
)

