FROM rust:1.33-stretch

LABEL maintainer="Evance Soumaoro <evanxg852000@gmail.com>"

# create app directory
RUN mkdir -p /usr/project
WORKDIR /usr/project

# this build step will cache your dependencies
COPY Cargo.toml ./
COPY Cargo.lock ./

# copy your source tree
COPY ./ /usr/project
RUN cargo build --release

EXPOSE 8080
ENTRYPOINT ["./entrypoint.sh"]
CMD ["bash"]