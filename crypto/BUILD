cc_import(
	name = "openssl",
)

cc_library(
	  visibility = [
			"//visibility:public",
		],
    name = "hash",
		hdrs = [
			  "hash.h",
		],
		srcs = [
			  "hash.cc",
		],    
		deps = [
			  "@abseil-cpp//absl/log:check",
  			"@abseil-cpp//absl/log:log",
			  "@abseil-cpp//absl/status:status",
				"@abseil-cpp//absl/status:statusor",
		],
)

cc_library(
    name = "crypto",
		],    
		deps = [
			  "@abseil-cpp//absl/log:check",
				"@abseil-cpp//absl/log:log",
			  "@abseil-cpp//absl/status:status",
				"@abseil-cpp//absl/status:statusor",
		],
)

c_test(
	  name = "hash_test",
		srcs = [
        "hash_test.cc",
		],
		deps = [
			  "@googletest//:gtest",
				"@googletest//:gtest_main",
		]
)
