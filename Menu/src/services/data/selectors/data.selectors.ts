import { IDataService } from "@services";

export const selectActiveWeapon = (state: IDataService) => state.activeWeapon;
export const selectDefaultSkins = (state: IDataService) => state.defaultSkins;
export const selectMapName = (state: IDataService) => state.mapName;
export const selectRadarData = (state: IDataService) => state.radarData;
export const selectSkins = (state: IDataService) => state.skins;
export const selectTeam = (state: IDataService) => state.team;