import { ItemDefinitionIndex, Skin } from "@utils";

export const GET_ALL_SKINS = "get_all_skins";

export type TGetAllSkinsInput = {
  type: "get_all_skins";
  message?: undefined;
};

export type TGetAllSkinsResponse = {
  type: "get_all_skins";
  message: {
    default: {
      [T in ItemDefinitionIndex | string]?: string;
    };
    skins: Skin[];
  };
};
