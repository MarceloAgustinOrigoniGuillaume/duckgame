target_sources(taller_common
    PRIVATE
    # .cpp files
        resolver.cpp
        socket.cpp
        liberror.cpp
        resolvererror.cpp
        protocol.cpp
        simplemessenger.cpp
    PUBLIC
    # .h files
        messenger.h
        resolver.h
        socket.h
        liberror.h
        resolvererror.h
        protocol.h
        simplemessenger.h

    )
