import React from "react";
import { useStyles } from "./styles";

export type HeaderProps = {
  title: string;
  onMinimize?: () => void;
  onOptions?: () => void;
  onClose?: () => void;
};
export const Header: React.FC<HeaderProps> = ({ title, onOptions, onMinimize, onClose }) => {
  const classes = useStyles();
  return (
    <div className={classes.header}>
      <div className={classes.header_title}>{title}</div>
      <div className={classes.header_actions}>
        <button className={`${classes.header_action} ${classes.header_action}-minimize`} onClick={onMinimize} />
        <button className={`${classes.header_action} ${classes.header_action}-options`} onClick={onOptions} />
        <button className={`${classes.header_action} ${classes.header_action}-close`} onClick={onClose} />
      </div>
    </div>
  );
};
