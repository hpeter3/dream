# OpenSSF recommendations
# link: https://best.openssf.org/Compiler-Hardening-Guides/Compiler-Options-Hardening-Guide-for-C-and-C++.html

# Hardening shouldn't be hardcoded
# Currently it's a -DENABLE_HARDENING flag, which is enabled by default but it can be disabled
# someone might use different hardening flags with different tools
if(NOT ENABLE_HARDENING)
    return()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(HARDEN_C_FLAGS
        -O2
        -Wall
        -Wformat
        -Wformat=2
        -Wconversion
        -Wimplicit-fallthrough
        -U_FORTIFY_SOURCE
        -D_FORTIFY_SOURCE=3
        -fstrict-flex-arrays=3
        -fstack-clash-protection
        -fstack-protector-strong
        -fPIE
    )
    set(HARDEN_CXX_FLAGS
        ${HARDEN_C_FLAGS} 
        -D_GLIBCXX_ASSERTIONS
    )
    set(HARDEN_LINK_FLAGS
        -pie
        -Wl,-z,relro
        -Wl,-z,nodlopen
        -Wl,-z,now
        -Wl,-z,noexecstack
        -Wl,--as-needed
    )
  # -Wl,--no-copy-dt-needed-entries needs some testing, Dream acts a little weird with this enabled on my machine
    target_compile_options(${PROJECT_NAME} PRIVATE ${HARDEN_CXX_FLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${HARDEN_LINK_FLAGS})
endif()
