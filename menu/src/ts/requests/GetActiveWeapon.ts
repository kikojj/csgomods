import { ItemDefinitionIndex } from "@utils";

export const GET_ACTIVE_WEAPON = "get_active_weapon";

export type TGetActiveWeaponInput = {
  type: "get_active_weapon";
  message?: undefined;
};

export type TGetActiveWeaponResponse = {
  type: "get_active_weapon";
  message: {
    active_weapon: ItemDefinitionIndex;
  };
};
