import React from "react";
import { IconButton, Logo } from "@components";

import { join } from "../utils";
import { useStyles } from "./styles";

export type TTab = {
  title: string;
  subtitle?: string;
  iconUrl: string;
  active?: boolean;
  onClick: () => void;
};
export type MenuProps = {
  tabs?: TTab[];
};
export const Menu: React.FC<MenuProps> = ({ tabs = [] }) => {
  const classes = useStyles();

  return (
    <div className={classes.contanier}>
      <Logo size="large" />
      <div className={classes.tabs}>
        {tabs.map((tab, key) => (
          <div
            key={key}
            className={join(classes.tab, tab.active ? `${classes.tab}-active` : undefined)}
            onClick={tab.onClick}
          >
            <div className={classes.tab_content}>
              <div className={classes.tab_content_text}>
                <div className={classes.tab_content_text_title}>{tab.title}</div>
                {tab.subtitle ? <div className={classes.tab_content_text_subtitle}>{tab.subtitle}</div> : ""}
              </div>
              <IconButton className={classes.tab_content_icon} iconUrl={tab.iconUrl} />
            </div>
            <div className={classes.tab_bg} />
          </div>
        ))}
      </div>
    </div>
  );
};
