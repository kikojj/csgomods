import React from "react";
import { useStyles } from "./styles";

export type TabProps = {
  title: string;
  active?: boolean;
  enable?: boolean;
  onClick?: () => void;
};
export const Tab: React.FC<TabProps> = ({ title, active = false, enable = false, onClick }) => {
  const classes = useStyles({ active, enable });
  return (
    <div className={classes.tab} onClick={onClick}>
      <div className={classes.tab_title}>{title}</div>
      <div className={classes.tab_badge} />
    </div>
  );
};
