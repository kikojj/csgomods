import React from "react";
import { Logo, Button } from "@components";
import { useStyles } from "./styles";
import { Tab, TabProps } from "./Tab";

export type MenuProps = {
  tabs?: TabProps[];
  onExit?: () => void;
};
export const Menu: React.FC<MenuProps> = ({ tabs = [], onExit }) => {
  const classes = useStyles();

  const tabsList = React.useMemo(
    () => tabs.map((tab) => <Tab key={tab.title} {...tab} />),
    [tabs]
  );

  return (
    <div className={classes.container}>
      <Logo size="large" />
      <div className={classes.tabs}>
        {tabsList}
        {onExit && (
          <Button className={classes.exit} marginTop={25} onClick={onExit}>
            Exit
          </Button>
        )}
      </div>
    </div>
  );
};
