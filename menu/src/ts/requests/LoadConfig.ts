export const LOAD_CONFIG = "load_config";

export type TLoadConfigInput = {
  type: "load_config";
  message: {
    fileName: string;
  };
};
