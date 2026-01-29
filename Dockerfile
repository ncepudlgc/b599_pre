FROM gcc:13-bookworm

# Install development tools and dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    valgrind \
    git \
    vim \
    nano \
    && rm -rf /var/lib/apt/lists/*

# Set up working directory
WORKDIR /app

# Copy source files
COPY . .

# Default to bash shell for interactive development
CMD ["/bin/bash"]