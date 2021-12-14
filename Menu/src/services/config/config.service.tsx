import { createStore, selectorFactory } from "okos";
import { send } from "@services";
import {
  TGetConfigsListResponse,
  GET_CONFIGS_LIST,
  SAVE_CONFIG,
  DELETE_CONFIG,
  LOAD_CONFIG,
} from "@ts/requests";

export interface IConfigService {
  configsList: string[];
}

const ConfigService = createStore({ configsList: [] } as IConfigService, {
  onGetConfigsList: (state, message: TGetConfigsListResponse["message"]) => {
    state.configsList = message.files;
  },
  getConfigsList: (_state) => {
    send({ type: GET_CONFIGS_LIST });
  },
  loadConfig: (_state, fileName: string) => {
    send({ type: LOAD_CONFIG, message: { file_name: fileName } });
  },
  saveConfig: (_state, fileName: string) => {
    send({
      type: SAVE_CONFIG,
      message: { file_name: fileName.split(".")[0] },
    });
  },
  deleteConfig: (_state, fileName: string) => {
    send({ type: DELETE_CONFIG, message: { file_name: fileName } });
  },
});

export const useConfigSelector = selectorFactory(ConfigService.store);

export const {
  onGetConfigsList,
  getConfigsList,
  loadConfig,
  saveConfig,
  deleteConfig,
} = ConfigService.actions;
