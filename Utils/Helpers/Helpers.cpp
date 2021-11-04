#include "Helpers.hpp"

void c_helpers::shoot() {
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(10);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void c_helpers::jump(){
	g_client.dw_force_jump(en_key_event::KeyDown);
	Sleep(10);
	g_client.dw_force_jump(en_key_event::KeyUp);
}

void c_helpers::keyboard_press_key(int key){
	keybd_event(key, 0, 0, 0);
	Sleep(10);
	keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
}

void c_helpers::toggle_steam_overlay(){
	keybd_event(VK_TAB, 0, 0, 0);
	keybd_event(VK_SHIFT, 0, 0, 0);
	Sleep(10);
	keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
}

bool c_helpers::is_mouse_active(){
	return (g_client.dw_input().mouse_active && (g_client.dw_mouse_enable() ^ (short)c_offsets::signatures::dw_mouse_enable_ptr) && !g_engine.is_overlay_active());
}

bool c_helpers::is_flashed(float flash){
	return flash > 120.f ? true : false;
}

void c_helpers::exit(){
	g_mem.free();
	g_mem.exit();
	std::exit(0);
}

int c_helpers::get_model_index(std::string name) {
	auto i_model_precache = g_engine.client_state->model_precache();
	auto i_model_base = g_mem.read<int>(g_mem.read<int>(i_model_precache + 0x40) + 0xC) + 0xC;

	for (int i = 0; i < 1024; i++) {
		auto i_model = g_mem.read<int>(i_model_base + (i * 0x34));

		std::string str_model = std::string(g_mem.read<std::array<char, 128>>(i_model).data());
		if (str_model.find(name) != std::string::npos) {
			return i;
		}
	}

	return -1;
}

int c_helpers::get_model_index(c_item::en_defenition_index di) {
	switch (di)
	{
	case c_item::en_defenition_index::WeaponKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_default_ct.mdl");
		break;
	case c_item::en_defenition_index::WeaponKnifeT:
		return c_helpers::get_model_index("models/weapons/v_knife_default_t.mdl");
		break;
	case c_item::en_defenition_index::WeaponBayonet:
		return c_helpers::get_model_index("models/weapons/v_knife_bayonet.mdl");
		break;
	case c_item::en_defenition_index::WeaponFlipKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_flip.mdl");
		break;
	case c_item::en_defenition_index::WeaponGutKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_gut.mdl");
		break;
	case c_item::en_defenition_index::WeaponKarambit:
		return c_helpers::get_model_index("models/weapons/v_knife_karam.mdl");
		break;
	case c_item::en_defenition_index::WeaponM9Bayonet:
		return c_helpers::get_model_index("models/weapons/v_knife_m9_bay.mdl");
		break;
	case c_item::en_defenition_index::WeaponHuntsmanKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_tactical.mdl");
		break;
	case c_item::en_defenition_index::WeaponFlachionKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_falchion_advanced.mdl");
		break;
	case c_item::en_defenition_index::WeaponBowieKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_survival_bowie.mdl");
		break;
	case c_item::en_defenition_index::WeaponButterflyKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_butterfly.mdl");
		break;
	case c_item::en_defenition_index::WeaponShadowDaggers:
		return c_helpers::get_model_index("models/weapons/v_knife_push.mdl");
		break;
	case c_item::en_defenition_index::WeaponUrsusKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_ursus.mdl");
		break;
	case c_item::en_defenition_index::WeaponNavajaKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_gypsy_jackknife.mdl");
		break;
	case c_item::en_defenition_index::WeaponStilettoKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_stiletto.mdl");
		break;
	case  c_item::en_defenition_index::WeaponTalonKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_widowmaker.mdl");
		break;
	case c_item::en_defenition_index::WeaponClassicKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_css.mdl");
		break;
	case c_item::en_defenition_index::WeaponParacordKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_cord.mdl");
		break;
	case c_item::en_defenition_index::WeaponSurvivalKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_canis.mdl");
		break;
	case c_item::en_defenition_index::WeaponNomadKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_outdoor.mdl");
		break;
	case c_item::en_defenition_index::WeaponSkeletonKnife:
		return c_helpers::get_model_index("models/weapons/v_knife_skeleton.mdl");
		break;
	default:
		return -1;
		break;
	}
}

void c_helpers::update_model_indexes(){
	if (g_engine.client_state->state() != en_client_states::InGame) {
		return;
	}

	auto vec_knifes = c_item::knifes();
	std::for_each(vec_knifes.begin(), vec_knifes.end(), [](c_item::en_defenition_index& di) {
		g_model_indexes[di] = get_model_index(di);
	});
}

void c_helpers::full_force_update(){
	//g_engine.client_state->delta_tick(-1);
}

bool c_helpers::world_to_screen(const D3DXVECTOR3 world, D3DXVECTOR2& screen, const RECT rect, const float matrix[16]) {
	float w = 0.0f;

	screen.x = matrix[0] * world.x + matrix[1] * world.y + matrix[2] * world.z + matrix[3];
	screen.y = matrix[4] * world.x + matrix[5] * world.y + matrix[6] * world.z + matrix[7];
	w = matrix[12] * world.x + matrix[13] * world.y + matrix[14] * world.z + matrix[15];

	if (w < 0.01f) {
		return false;
	}

	const float invw = 1.0f / w;
	screen.x *= invw;
	screen.y *= invw;

	int width = static_cast<int>(rect.right - rect.left);
	int height = static_cast<int>(rect.bottom - rect.top);

	float x = float(width / 2);
	float y = float(height / 2);

	x += float(screen.x * x);
	y -= float(screen.y * y);

	screen.x = x + rect.left;
	screen.y = y + rect.top;

	return true;
}