import { ISocketService } from "@services";

export const selectConnected = (state: ISocketService) => state.connected;

export const selectSocket = (state: ISocketService) => state.socket;