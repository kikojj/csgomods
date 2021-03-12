import { TSettings } from "@utils";

export const UPDATE_SETTINGS = "update_settings";

export type TUpdateSettingsInput = {
  type: "update_settings";
  message: TSettings;
};
