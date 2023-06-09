#include "../include/plataniumv3gui.hpp"

int main(void)
{
	spdlog::set_level(spdlog::level::level_enum::trace);
	read_config();
	
	if (!g_configuration->deviceAuth.account_id.empty() && !g_configuration->deviceAuth.device_id.empty() && !g_configuration->deviceAuth.secret.empty())
	{
		epic_account_t* user = new epic_account_t();
		if (!PLATANIUM_OK(platalog_error(epic_login_with_device_auth(g_configuration->deviceAuth, user), "epic_login_with_device_auth")))
		{
			memset(&g_configuration->deviceAuth, 0, sizeof(epic_device_auth_t));
			write_configuration();
			spdlog::info("{} - successfully destroyed current device auth because it was invalid", __FUNCTION__);
			delete user;
		}
	}

	GLFWwindow* window;

	if (!create_window(&window))
	{
		spdlog::info("{} - Closing app.", __FUNCTION__);
		return 1;
	}

	initialize_imgui(window);
	window_loop(window);
	cleanup_window(window);

	return 0;
}