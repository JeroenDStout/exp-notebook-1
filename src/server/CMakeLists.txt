init_directory(server)

# Define the Server project
init_project(server "core")

# Sources static
setup_project_source(server "server"
  src:
    server.cpp
  include:
    server.h
    uwebsockets.h
)

# Target
configure_project_executable(server)
configure_cxx_target(server)
configure_project_uwebsockets(server)
