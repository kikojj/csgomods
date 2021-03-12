import React from "react";
import { SettingsContext } from "../../contexts";
import { Header as _Header } from "../../components";

export type HeaderProps = {
  onOptions?: () => void;
};
export const Header: React.FC<HeaderProps> = ({ onOptions }) => {
  const { closeMenu } = React.useContext(SettingsContext);
  return <_Header title="csgomods" onMinimize={closeMenu} onOptions={onOptions} />;
};
