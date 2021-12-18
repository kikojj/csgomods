import React from "react";
import { ITrackProps } from "react-range/lib/types";
import { useStyles } from "./styles";

export type TrackProps = {
  color: string;
  valueInPercents: number;
  props: ITrackProps;
  isDragged: boolean;
  disabled: boolean;
  children: React.ReactNode;
};
export const Track: React.FC<TrackProps> = ({
  color,
  valueInPercents,
  props: { ref, style, onMouseDown, onTouchStart },
  children,
}) => {
  const classes = useStyles({ color, valueInPercents });

  return (
    <div
      onMouseDown={onMouseDown}
      onTouchStart={onTouchStart}
      style={style}
      className={classes.trackBackground}
    >
      <div ref={ref} className={classes.trackValue}>
        {children}
      </div>
    </div>
  );
};
