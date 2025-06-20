cc_library(
	  visibility = [
			"//visibility:public",
		],
    name = "buffer",
		hdrs = [
			  "buffer.h",
		],
		srcs = [
			  "buffer.cc",
		],    
		deps = [
			  "@abseil-cpp//absl/log:check",
  			"@abseil-cpp//absl/log:log",
			  "@abseil-cpp//absl/status:status",
				"@abseil-cpp//absl/status:statusor",
		],
)

#cc_library(
#    name = "crypto",
#		deps = [
#			  "@abseil-cpp//absl/log:check",
#				"@abseil-cpp//absl/log:log",
#			  "@abseil-cpp//absl/status:status",
#				"@abseil-cpp//absl/status:statusor",
#				":hash",
#		],
#)

cc_test(
	  name = "buffer_test",
		srcs = [
        "buffer_test.cc",
		],
		deps = [
			  "@googletest//:gtest",
				"@googletest//:gtest_main",
				":buffer",
		]
)
