cc_library(
	  visibility = [
			"//visibility:public",
		],
    name = "net",
		srcs = [
			  "closer.cc",
				"closer.h",
				"epoll_fd.cc",
			  "epoll_fd.h",
			  "net.cc",
			  "net.h",
		],
		deps = [
			  "@abseil-cpp//absl/log:check",
				"@abseil-cpp//absl/log:log",
			  "@abseil-cpp//absl/status:status",
		],
)

cc_test(
	  name = "net_test",
		srcs = [
        "net_test.cc",
		],
		deps = [
			  "@googletest//:gtest",
				"@googletest//:gtest_main",
		]
)
