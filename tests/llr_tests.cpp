#include<gtest/gtest.h>
#include<llr/api.h>
#include<wnd/window.h>



TEST(llr_tests, sample) {
	wnd::Window window(800, 600, "Unit Tests");
	llr::llr llr(window);
}