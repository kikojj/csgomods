export const GET_CONFIGS_LIST = "get_configs_list";

export type TConfigsListInput = {
  type: "get_configs_list";
  message?: undefined;
};

export type TGetConfigsListResponse = {
  type: "get_configs_list";
  message: { files: string[] };
};
