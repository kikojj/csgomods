import { TSettings } from "@utils";

export const GET_ALL_SETTINGS = "get_all_settings";

export type TGetAllSettingsResponse = {
  type: "get_all_settings";
  message: TSettings;
};
