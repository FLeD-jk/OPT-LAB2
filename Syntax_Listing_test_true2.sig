<signal-program>
    <program>
        401 PROGRAM
        <procedureidentifier>
            <identifier>
                1001 PROG2
        59 ;
        <block>
            402 BEGIN
            <statementslist>
                <statement>
                    <conditionstatement>
                        <incompletecondition-statement > 
                            408 IF
                            <conditional-expression>
                                <expression>
                                    <unsigned-integer>
                                        501 10
                                <comparison-operator>
                                    62 >
                                <expression>
                                    <unsigned-integer>
                                        502 2
                            409 THEN
                            <statements-list>
                                <statement>
                                    405 WHILE
                                    <conditional-expression>
                                        <expression>
                                            <variable-identifier>
                                                <identifier>
                                                    1002 VAR1
                                        <comparison-operator>
                                            302 <>
                                        <expression>
                                            <variable-identifier>
                                                <identifier>
                                                    1003 VAR2
                                    406 DO
                                    <statements-list>
                                        <empty>
                                    407 ENDWHILE
                                    59 ;
                                <statements-list>
                                    <empty>
                        <alternativepart>
                            <empty>
                    404 ENDIF
                    59 ;
                <statements-list>
                    <statement>
                        405 WHILE
                        <conditional-expression>
                            <expression>
                                <variable-identifier>
                                    <identifier>
                                        1002 VAR1
                            <comparison-operator>
                                302 <>
                            <expression>
                                <variable-identifier>
                                    <identifier>
                                        1003 VAR2
                        406 DO
                        <statements-list>
                            <statement>
                                <conditionstatement>
                                    <incompletecondition-statement > 
                                        408 IF
                                        <conditional-expression>
                                            <expression>
                                                <unsigned-integer>
                                                    501 10
                                            <comparison-operator>
                                                62 >
                                            <expression>
                                                <unsigned-integer>
                                                    502 2
                                        409 THEN
                                        <statements-list>
                                            <empty>
                                    <alternativepart>
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

