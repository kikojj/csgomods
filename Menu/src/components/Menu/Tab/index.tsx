import React from "react";
import { IconButton } from "@components";
import { join } from "@components/utils";
import { useStyles } from "./styles";

export type TabProps = {
  title: string;
  subtitle?: string;
  iconUrl: string;
  active?: boolean;
  onClick: () => void;
};
export const Tab: React.FC<TabProps> = ({
  title,
  subtitle,
  iconUrl,
  active,
  onClick,
}) => {
  const classes = useStyles();

  return (
    <div
      className={join(
        classes.tab,
        active && `${classes.tab}-active`
      )}
      onClick={onClick}
    >
      <div className={classes.tab_content}>
        <div className={classes.tab_content_text}>
          <div className={classes.tab_content_text_title}>{title}</div>
          {subtitle && (
            <div className={classes.tab_content_text_subtitle}>{subtitle}</div>
          )}
        </div>
        <IconButton iconUrl={iconUrl} />
      </div>
      <div className={classes.tab_bg} />
    </div>
  );
};
