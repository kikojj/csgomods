export const DELETE_CONFIG = "delete_config";

export type TDeleteConfigInput = {
  type: "delete_config";
  message: {
    fileName: string;
  };
};
