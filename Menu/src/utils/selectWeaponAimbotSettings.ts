import { IAimbotSettings, ItemDefinitionIndex, TSettings } from "@utils";

export const selectWeaponAimbotSettings = (settings: TSettings, weaponDI: ItemDefinitionIndex, weaponSectionName: string): IAimbotSettings => {
    const weaponAimbotSettings = settings.aimbot_weapons[weaponDI];
    const hasUsedWeaponAimbotSettings = weaponAimbotSettings && weaponAimbotSettings.use;

    const weaponSectionKey = `aimbot_${weaponSectionName}` as keyof TSettings;
    const weaponSectionAimbotSettings = settings[weaponSectionKey] as IAimbotSettings;
    const hasUsedWeaponSectionAimbotSettings = weaponSectionAimbotSettings && weaponSectionAimbotSettings.use;

    if (hasUsedWeaponAimbotSettings) {
        return weaponAimbotSettings;
    }

    if (hasUsedWeaponSectionAimbotSettings) {
        return weaponSectionAimbotSettings;
    }

    return settings.aimbot_global;
}