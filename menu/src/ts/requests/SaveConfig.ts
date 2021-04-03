export const SAVE_CONFIG = "save_config";

export type TSaveConfigInput = {
  type: "save_config";
  message: {
    file_name: string;
  };
};
