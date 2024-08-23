
git submodule set-url third_party/abseil-cpp git@github.com:abseil/abseil-cpp.git
git submodule set-url third_party/benchmark git@github.com:google/benchmark
git submodule set-url third_party/bloaty git@github.com:google/bloaty.git
git submodule set-url third_party/boringssl-with-bazel git@github.com:google/boringssl.git
git submodule set-url third_party/cares/cares git@github.com:c-ares/c-ares.git
git submodule set-url third_party/envoy-api git@github.com:envoyproxy/data-plane-api.git
git submodule set-url third_party/googleapis git@github.com:googleapis/googleapis.git
git submodule set-url third_party/googletest git@github.com:google/googletest.git
git submodule set-url third_party/opencensus-proto git@github.com:census-instrumentation/opencensus-proto.git
git submodule set-url third_party/opentelemetry git@github.com:open-telemetry/opentelemetry-proto.git
git submodule set-url third_party/protobuf git@github.com:protocolbuffers/protobuf.git 
git submodule set-url third_party/protoc-gen-validate git@github.com:envoyproxy/protoc-gen-validate.git
git submodule set-url third_party/re2 git@github.com:google/re2.git
git submodule set-url third_party/xds git@github.com:cncf/xds.git
git submodule set-url third_party/zlib git@github.com:madler/zlib


cd third_party/protobuf 
git submodule set-url third_party/googletest git@github.com:google/googletest.git
git submodule set-url third_party/abseil-cpp git@github.com:abseil/abseil-cpp.git
git submodule set-url third_party/jsoncpp git@github.com:open-source-parsers/jsoncpp.git

cd ../../