import React from "react";
import { Range as RRange } from "react-range";

import { colors } from "@utils";
import { join } from "../utils";

import { useStyles } from "./styles";

export type RangeProps = {
  className?: string;
  type?: "int" | "float";
  value?: number;
  onChange?: (n: number) => void;
  min?: number;
  max?: number;
  step?: number;
  color?: string;
  onClick?: (e: React.MouseEvent<HTMLDivElement, globalThis.MouseEvent>) => void;
};
export const Range: React.FC<RangeProps> = ({
  className,
  value: _value,
  onChange: _onChange,
  type = "int",
  min = 0,
  max = 100,
  step = 1,
  color = colors.primary,
  onClick,
}) => {
  const [__value, __onChange] = React.useState<number>(min);

  let value = _value !== undefined && _onChange !== undefined ? _value : __value;
  let onChange = _value !== undefined && _onChange !== undefined ? _onChange : __onChange;

  const classes = useStyles({ value: ((value - min) / (max - min)) * 100, type, color });

  return (
    <div className={join(classes.container, className)} onClick={onClick}>
      {type === "float" ? (
        <button className={classes.btn_minus} onClick={() => onChange(value - step < min ? min : value - step)}>
          -
        </button>
      ) : (
        ""
      )}
      <div className={classes.content}>
        <RRange
          values={[value]}
          step={step}
          min={min}
          max={max}
          onChange={(values) => onChange(values[0])}
          renderTrack={({ props, children }) => (
            <div
              onMouseDown={props.onMouseDown}
              onTouchStart={props.onTouchStart}
              style={props.style}
              className={classes.trackBackground}
            >
              <div ref={props.ref} className={classes.trackValue}>
                {children}
              </div>
            </div>
          )}
          renderThumb={({ props, isDragged }) => <div {...props} className={classes.valueMark} />}
        />
      </div>
      {type === "float" ? (
        <button className={classes.btn_plus} onClick={() => onChange(value + step > max ? max : value + step)}>
          +
        </button>
      ) : (
        ""
      )}
    </div>
  );
};
