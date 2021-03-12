import React from "react";
import { useStyles } from "./styles";

export type GroupProps = {
  label?: string;
  width?: string | number;
  marginTop?: number;
  marginLeft?: number;
};
export const Group: React.FC<GroupProps> = ({ label, width = 300, children, marginTop = 0, marginLeft = 0 }) => {
  const classes = useStyles({ width });

  return (
    <div className={classes.container} style={{ marginTop, marginLeft }}>
      {label ? (
        <div className={classes.label}>
          <div className={classes.label_text}>{label}</div>
          <div className={classes.label_border} />
        </div>
      ) : (
        ""
      )}
      {children ? <div className={classes.content}>{children}</div> : ""}
    </div>
  );
};
