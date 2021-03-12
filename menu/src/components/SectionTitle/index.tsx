import React from "react";

import { FormControlLabel, Switch as _Switch } from "@material-ui/core";
import { useStyles } from "./styles";

export type SectionTitleProps = {
  text: string;
};
export const SectionTitle: React.FC<SectionTitleProps> = ({ text }) => {
  const classes = useStyles();
  return <h6 className={classes.text}>{text}</h6>;
};
