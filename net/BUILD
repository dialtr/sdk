cc_library(
	  visibility = [
			"//visibility:public",
		],
    name = "net",
		hdrs = [
			"closer.h",
			"epoll_fd.h",
			"net.h",
		],
		srcs = [
			  "closer.cc",
				"epoll_fd.cc",
			  "net.cc",
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
