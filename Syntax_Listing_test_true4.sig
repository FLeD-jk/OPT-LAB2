<signal-program>
    <program>
        401 PROGRAM
        <procedureidentifier>
            <identifier>
                1001 LAB2OPT
        59 ;
        <block>
            402 BEGIN
            <statements-list>
                <statement>
                    405 WHILE
                    <conditional-expression>
                        <expression>
                            <variable-identifier>
                                <identifier>
                                    1002 VAR1
                        <comparison-operator>
                            61 =
                        <expression>
                            <variable-identifier>
                                <identifier>
                                    1003 VAR4
                    406 DO
                    <statements-list>
                        <statement>
                            <conditionstatement>
                                <incompletecondition-statement>
                                    408 IF
                                    <conditional-expression>
                                        <expression>
                                            <unsigned-integer>
                                                501 24
                                        <comparison-operator>
                                            301 <=
                                        <expression>
                                            <unsigned-integer>
                                                502 56
                                    409 THEN
                                    <statements-list>
                                        <empty>
                                <alternativepart>
                                    410 ELSE
                                    <statements-list>
                                        <statement>
                                            405 WHILE
                                            <conditional-expression>
                                                <expression>
                                                    <variable-identifier>
                                                        <identifier>
                                                            1002 VAR1
                                                <comparison-operator>
                                                    61 =
                                                <expression>
                                                    <variable-identifier>
                                                        <identifier>
                                                            1003 VAR4
                                            406 DO
                                            <statements-list>
                                                <empty>
                                            407 ENDWHILE
                                            59 ;
                                        <statements-list>
                                            <empty>
                            404 ENDIF
                            59 ;
                        <statements-list>
                            <empty>
                    407 ENDWHILE
                    59 ;
                <statements-list>
                    <empty>
            403 END
        46 .

